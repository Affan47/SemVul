RecordLoadedModule (
    StructInitInfo *        info,
    Char *filename )
{
  UInt len;
    if ( NrModules == MAX_MODULES ) {
        Pr( "panic: no room to record module\n", 0L, 0L );
    }
    len = strlen(filename);
    if (NextLoadedModuleFilename + len + 1
        > LoadedModuleFilenames+MAX_MODULE_FILENAMES) {
      Pr( "panic: no room for module filename\n", 0L, 0L );
    }
    *NextLoadedModuleFilename = '\0';
    SyStrncat(NextLoadedModuleFilename,filename, len);
    info->filename = NextLoadedModuleFilename;
    NextLoadedModuleFilename += len +1;
    Modules[NrModules++] = info;
}
