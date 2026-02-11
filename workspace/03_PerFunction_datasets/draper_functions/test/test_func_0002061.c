bm_open(char *bm_file_name) {
    BuzzMachineHandle *bmh=(BuzzMachineHandle *)calloc(sizeof(BuzzMachineHandle),1);
    GetInfoPtr GetInfo=NULL;
    CreateMachinePtr CreateMachine=NULL;

#ifdef WIN32
    bmh->h=(void*)LoadLibraryA(bm_file_name);
#else
    bmh->h=dlopen(bm_file_name,RTLD_LAZY);
#endif
    if(!bmh->h) {
#ifdef WIN32
        DBG1("  failed to load machine dll from \"%s\"\n",bm_file_name);
#else
        DBG2("  failed to load machine dll from \"%s\": %s\n",bm_file_name,dlerror());
#endif
        bm_close(bmh);
        return(NULL);
    }
    DBG1("  dll %s loaded\n",bm_file_name);
    bmh->lib_name=strdup(bm_file_name);


#ifdef WIN32
    GetInfo      =(GetInfoPtr      )GetProcAddress((HMODULE)(bmh->h),"GetInfo");
    CreateMachine=(CreateMachinePtr)GetProcAddress((HMODULE)(bmh->h),"CreateMachine");
#else
    GetInfo      =(GetInfoPtr      )dlsym(bmh->h,"GetInfo");
    CreateMachine=(CreateMachinePtr)dlsym(bmh->h,"CreateMachine");
#endif
    if(!GetInfo) {
        DBG("  failed to connect to GetInfo method\n");
        bm_close(bmh);
        return(NULL);
    }
    if(!CreateMachine) {
        DBG("  failed to connect to GreateMachine method\n");
        bm_close(bmh);
        return(NULL);
    }
    bmh->CreateMachine=CreateMachine;
    DBG("  symbols connected\n");


    bmh->machine_info=GetInfo();
    DBG("  GetInfo() called\n");


    if(!bmh->machine_info->minTracks) {
        if(bmh->machine_info->numTrackParameters) {
            DBG("!! buggy machine, numTrackParams>0, but minTracks=0\n");
            bmh->machine_info->numTrackParameters=0;
        }
        if(bmh->machine_info->maxTracks) {
            DBG("!! buggy machine, maxTracks>0, but minTracks=0\n");
            bmh->machine_info->maxTracks=0;
        }
    }


    if((bmh->bm=bm_new(bmh))) {
      bm_init(bmh->bm,0,NULL);
      if(bmh->bm->mdkHelper) {
        if(bmh->bm->mdkHelper->numChannels) {
          bmh->mdk_num_channels=bmh->bm->mdkHelper->numChannels;
        }
      }
    }
    else {
      DBG("  CreateMachine() failed\n");
      bm_close(bmh);
      return(NULL);
    }

    return(bmh);
}
