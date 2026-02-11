show_attrs(gxml_data * xd, int etype, const char ** attr)
{
    int count;
    show_depth(xd->depth, 1, stderr);
    fprintf(stderr, ": element %s\n", enames[etype]);
    for( count = 0; attr[count]; count += 2 ){
        show_depth(xd->depth, 0, stderr);
        fprintf(stderr,"      attr: %s='%s'\n", attr[count], attr[count+1]);
    }
}
