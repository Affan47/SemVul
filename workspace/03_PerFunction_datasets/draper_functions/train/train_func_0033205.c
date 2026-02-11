property_page_store_creation_tag(struct property_page *pp,
                                             int tag, int count)
{
  if (!pp || !pp->tag_table) {
    return;
  }

  if (stored_tag_hash_lookup(pp->tag_table, tag, NULL)) {
    log_error("Attempted to insert object creation tag %d "
              "twice into tag table for property page %p (%d %s).",
              tag, pp, property_page_get_objtype(pp),
              property_page_get_name(pp));
    return;
  }

  stored_tag_hash_insert(pp->tag_table, tag, count);
}
