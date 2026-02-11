save_mtab() {
    FILE *mtab;
    mnt_node *mnt,*next;
    mtab=setmntent(mtab_filename,"w");
    for(mnt=mounted_list;mnt;mnt=next) {
	addmntent(mtab,&mnt->ms);
	next=mnt->next;
	free_mtab_node(mnt);
    }
    mounted_list=mounted_list_end=NULL;
    endmntent(mtab);
    mtab_changed=0;
}
