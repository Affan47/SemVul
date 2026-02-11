hdup_globfilecheck(char *globpath, char **firstmatch)
{


	glob_t globbuf;
	if (globpath == NULL )
		return 0;


	glob(globpath,0,NULL,&globbuf);

	if ( globbuf.gl_pathc > 0 ) {

		if ( firstmatch != NULL ) {
			*firstmatch = g_strdup(globbuf.gl_pathv[0]);
		}
		globfree(&globbuf);
		return 1;
	} else {
		globfree(&globbuf);
		return 0;
	}
}
