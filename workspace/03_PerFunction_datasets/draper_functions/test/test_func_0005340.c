FCEUSS_CheckStates(void)
{
        FILE *st=NULL;
        char *fn;
        int ssel;

        for(ssel=0;ssel<10;ssel++)
        {
         st=FCEUD_UTF8fopen(fn=FCEU_MakeFName(FCEUMKF_STATE,ssel,0),"rb");
         free(fn);
         if(st)
         {
          SaveStateStatus[ssel]=1;
          fclose(st);
         }
         else
          SaveStateStatus[ssel]=0;
        }

	CurrentState=0;
	StateShow=0;
}
