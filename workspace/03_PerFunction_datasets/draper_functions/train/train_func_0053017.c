expand_handler_elements(const String& pattern, const String& handler_name,
			Vector<Element*>& elements, Router* router)
{

    if (Element* e = router->find(pattern)) {
	elements.push_back(e);
	return 1;
    }

    bool is_pattern = false;
    for (const char* s = pattern.begin(); s < pattern.end(); s++)
	if (*s == '?' || *s == '*' || *s == '[') {
	    is_pattern = true;
	    break;
	}

    bool any = false;
    for (int i = 0; i < router->nelements(); i++)
	if (is_pattern
	    ? glob_match(router->ename(i), pattern)
	    : router->element(i)->cast(pattern.c_str()) != 0) {
	    any = true;
	    const Handler* h = Router::handler(router->element(i), handler_name);
	    if (h && h->read_visible())
		elements.push_back(router->element(i));
	}
    if (!any)
	return errh->error((is_pattern ? "no element matching '%s'" : "no element '%s'"), pattern.c_str());
    else
	return 2;
}
