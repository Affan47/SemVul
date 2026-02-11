gg_svg_parse_header (struct gg_svg_document *gg_svg_doc, struct _xmlAttr *attr)
{

    while (attr)
      {
	  if (attr->type == XML_ATTRIBUTE_NODE)
	    {
		const char *value = NULL;
		const char *name;
		xmlNodePtr child = attr->children;
		name = (const char *) (attr->name);
		if (child)
		    value = (const char *) (child->content);
		if (child && value)
		  {
		      int len;
		      double factor = 1.0;
		      if (strcmp (name, "width") == 0)
			{
			    len = strlen (value);
			    if (len > 3)
			      {
				  if (strcmp (value + len - 2, "mm") == 0)
				      factor = 72.0 / 25.4;
				  else if (strcmp (value + len - 2, "cm") == 0)
				      factor = 72.0 / 2.54;
				  else if (strcmp (value + len - 2, "in") == 0)
				      factor = 72.0;
				  else if (strcmp (value + len - 2, "pc") == 0)
				      factor = 72.0 / 6.0;
			      }
			    gg_svg_doc->width = atof (value) * factor;
			}
		      if (strcmp (name, "height") == 0)
			{
			    len = strlen (value);
			    if (len > 3)
			      {
				  if (strcmp (value + len - 2, "mm") == 0)
				      factor = 72.0 / 25.4;
				  else if (strcmp (value + len - 2, "cm") == 0)
				      factor = 72.0 / 2.54;
				  else if (strcmp (value + len - 2, "in") == 0)
				      factor = 72.0;
				  else if (strcmp (value + len - 2, "pc") == 0)
				      factor = 72.0 / 6.0;
			      }
			    gg_svg_doc->height = atof (value) * factor;
			}
		      if (strcmp (name, "viewBox") == 0)
			  gg_svg_parse_viewbox (gg_svg_doc, value);
		  }
	    }
	  attr = attr->next;
      }
}
