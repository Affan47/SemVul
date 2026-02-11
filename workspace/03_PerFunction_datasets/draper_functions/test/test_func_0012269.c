Define_Class (char *name, WidgetClass class, XtResourceList r, int nr) {
    Set_Error_Tag ("define-class");
    if (clast == ctab+MAX_CLASS)
        Primitive_Error ("too many widget classes");


    clast->name = name;
    clast->class = class;
    clast->cb[0].name = XtNdestroyCallback;
    clast->cb[0].has_arg = 0;
    clast->cblast = clast->cb+1;
    clast->sub_resources = r;
    clast->num_resources = nr;
    clast++;
}
