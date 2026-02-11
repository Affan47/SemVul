SMfreearticle(ARTHANDLE *article) {
    if (method_data[typetoindex[article->type]].initialized == INIT_FAIL) {
	return;
    }
    if (method_data[typetoindex[article->type]].initialized == INIT_NO && !InitMethod(typetoindex[article->type])) {
	warn("SM: can't free article with uninitialized method");
	return;
    }
    storage_methods[typetoindex[article->type]].freearticle(article);
}
