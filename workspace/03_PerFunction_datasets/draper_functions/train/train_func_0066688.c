waypt_add_url(waypoint *wpt, char *link, char *url_link_text)
{
  if ((link == NULL) && (url_link_text == NULL)) {
    return;
  }


  if ((wpt->url == NULL)  && (wpt->url_link_text == NULL)) {
    wpt->url = link;
    wpt->url_link_text = url_link_text;
  } else {
    url_link *tail;
    url_link *new_link = (url_link*) xcalloc(sizeof(url_link), 1);
    new_link->url = link;
    new_link->url_link_text = url_link_text;


    for (tail = wpt->url_next;; tail = tail->url_next) {
      if (tail == NULL) {
        wpt->url_next = new_link;
        break;
      }
      if (tail->url_next == NULL) {
        tail->url_next = new_link;
        break;
      }
    }
  }
}
