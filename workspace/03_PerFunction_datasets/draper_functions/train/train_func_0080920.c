new_rmff_cont(const char *title, const char *author, const char *copyright, const char *comment)
{

    struct rmff_cont_t *cont = xmalloc(sizeof(struct rmff_cont_t));

    cont->object_id=CONT_TAG;
    cont->object_version=0;

    cont->title=NULL;
    cont->author=NULL;
    cont->copyright=NULL;
    cont->comment=NULL;

    cont->title_len=0;
    cont->author_len=0;
    cont->copyright_len=0;
    cont->comment_len=0;

    if (title) {
	cont->title_len=strlen(title);
	cont->title=strdup(title);
    }
    if (author) {
	cont->author_len=strlen(author);
	cont->author=strdup(author);
    }
    if (copyright) {
	cont->copyright_len=strlen(copyright);
	cont->copyright=strdup(copyright);
    }
    if (comment) {
	cont->comment_len=strlen(comment);
	cont->comment=strdup(comment);
    }
    cont->size=cont->title_len+cont->author_len+cont->copyright_len+cont->comment_len+18;

    return cont;
}
