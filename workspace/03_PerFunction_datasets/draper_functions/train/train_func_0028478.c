transport_flip(void){
  if( g.urlIsSsh ){
    fprintf(sshOut, "\n\n");
  }else if( g.urlIsFile ){
    char *zCmd;
    fclose(transport.pFile);
    zCmd = mprintf("\"%s\" http \"%s\" \"%s\" \"%s\" 127.0.0.1 --localauth",
       g.nameOfExe, g.urlName, transport.zOutFile, transport.zInFile
    );
    fossil_system(zCmd);
    free(zCmd);
    transport.pFile = fossil_fopen(transport.zInFile, "rb");
  }
}
