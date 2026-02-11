zx_DEC_ELEM_hrxml_OtherPublication(struct zx_ctx* c, struct zx_hrxml_OtherPublication_s* x)
{
  struct zx_elem_s* el = x->gg.kids;
  switch (el->g.tok) {
  case zx_hrxml_Title_ELEM:
    if (!x->Title)
      x->Title = el;
    return 1;
  case zx_hrxml_Name_ELEM:
    if (!x->Name)
      x->Name = el;
    return 1;
  case zx_hrxml_PublicationDate_ELEM:
    if (!x->PublicationDate)
      x->PublicationDate = (struct zx_hrxml_PublicationDate_s*)el;
    return 1;
  case zx_hrxml_Link_ELEM:
    if (!x->Link)
      x->Link = el;
    return 1;
  case zx_hrxml_Abstract_ELEM:
    if (!x->Abstract)
      x->Abstract = el;
    return 1;
  case zx_hrxml_Copyright_ELEM:
    if (!x->Copyright)
      x->Copyright = (struct zx_hrxml_Copyright_s*)el;
    return 1;
  case zx_hrxml_Comments_ELEM:
    if (!x->Comments)
      x->Comments = el;
    return 1;
  case zx_hrxml_ISSN_ELEM:
    if (!x->ISSN)
      x->ISSN = el;
    return 1;
  case zx_hrxml_ISBN_ELEM:
    if (!x->ISBN)
      x->ISBN = el;
    return 1;
  case zx_hrxml_NumberOfPages_ELEM:
    if (!x->NumberOfPages)
      x->NumberOfPages = el;
    return 1;
  case zx_hrxml_PublisherName_ELEM:
    if (!x->PublisherName)
      x->PublisherName = el;
    return 1;
  case zx_hrxml_PublisherLocation_ELEM:
    if (!x->PublisherLocation)
      x->PublisherLocation = el;
    return 1;

  default: return 0;
  }
}
