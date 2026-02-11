dom_namednode_iter(dom_object *basenode, int ntype, dom_object *intern, xmlHashTablePtr ht, xmlChar *local, xmlChar *ns TSRMLS_DC)
{
	dom_nnodemap_object *mapptr;
	zval *baseobj = NULL;

	mapptr = (dom_nnodemap_object *)intern->ptr;
	if (basenode) {
		MAKE_STD_ZVAL(baseobj);
		baseobj->type = IS_OBJECT;
		Z_SET_ISREF_P(baseobj);
		baseobj->value.obj.handle = basenode->handle;
		baseobj->value.obj.handlers = dom_get_obj_handlers(TSRMLS_C);
		zval_copy_ctor(baseobj);
	}
	mapptr->baseobjptr = baseobj;
	mapptr->baseobj = basenode;
	mapptr->nodetype = ntype;
	mapptr->ht = ht;
	mapptr->local = local;
	mapptr->ns = ns;

}
