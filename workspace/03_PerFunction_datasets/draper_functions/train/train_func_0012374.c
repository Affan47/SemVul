dict_add_handle(FILE *_handle)
{
		FILE **save;
		dict.handles = (FILE **)realloc(save=dict.handles,sizeof(FILE *)*(dict.n_handles+1));
		if(!dict.handles) {
				dict.handles=save;
				return 1;
		}
		dict.handles[dict.n_handles]=_handle;
		dict.n_handles++;
		return 0;
}
