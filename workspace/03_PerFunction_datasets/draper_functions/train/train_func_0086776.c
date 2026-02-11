compare_folders_alpha_dir(FOLDER_S *f1, FOLDER_S *f2)
{
    int	  i;

    if((i = (f1->isdir - f2->isdir)) == 0){
	char *f1name = FLDR_NAME(f1),
	     *f2name = FLDR_NAME(f2);

	return(compare_names(&f1name, &f2name));
    }

    return(i);
}
