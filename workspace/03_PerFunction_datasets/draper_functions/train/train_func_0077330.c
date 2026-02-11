remove_ns(ATTRIBUTE_UNUSED PyObject *self, PyObject *args) {
PyObject *pyobj_tree,*pyobj_ns;
xmlNsPtr nsDef,prev;
xmlNodePtr node;
xmlNodePtr declNode = NULL;
xmlAttrPtr attr;
xmlNodePtr tree;
xmlNsPtr ns;

	if (!PyArg_ParseTuple(args, "OO", &pyobj_tree,&pyobj_ns)) return NULL;
	tree = (xmlNodePtr) PyxmlNode_Get(pyobj_tree);
	ns = (xmlNsPtr) PyxmlNode_Get(pyobj_ns);
	node = tree;

	if (ns == NULL) {
		PyErr_SetString(MyError,"remove_ns: NULL namespace");
		return NULL;
	}

	while (node != NULL) {


		if (node->ns == ns) {
			PyErr_SetString(MyError,"remove_ns: NULL namespace");
			return NULL;
		}


		attr = node->properties;
		while (attr != NULL) {
			if (attr->ns == ns) {
				PyErr_SetString(MyError,"remove_ns: NULL namespace");
				return NULL;
			}
			attr = attr->next;
		}


		nsDef=node->nsDef;
		while(nsDef != NULL) {
			if (nsDef == ns) {
				declNode = node;
				break;
			}
			nsDef=nsDef->next;
		}


		if (node->children != NULL) {

			node = node->children;
		} else if ((node != tree) && (node->next != NULL)) {

			node = node->next;
		} else if (node != tree) {

			while (node != tree) {
				if (node->parent != NULL)
					node = node->parent;
				if ((node != tree) && (node->next != NULL)) {
					node = node->next;
					break;
				}
				if (node->parent == NULL) {
				    node = NULL;
				    break;
				}
			}

			if (node == tree) node = NULL;
		} else break;
		if (node == tree) break;
	}


	if (declNode == NULL) {
		Py_INCREF(Py_None);
		return Py_None;
	}

	prev=NULL;
	nsDef=declNode->nsDef;
	while(nsDef != NULL) {
		if (nsDef == ns) {
			if (prev == NULL) declNode->nsDef=nsDef->next;
			else prev->next=nsDef->next;
			xmlFreeNs(ns);
			break;
		}
		prev=nsDef;
		nsDef=nsDef->next;
	}

	Py_INCREF(Py_None);
	return Py_None;
}
