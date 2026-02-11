rum_element_display(const rum_element_t *element)
{
    rum_set_error(NULL);
    if (element) {
        rum_tag_display_element(element->tag, element);
        if (element->first_child) {
            rum_element_display(element->first_child);
        }
        if (element->next_sibling) {
            rum_element_display(element->next_sibling);
        }
    }
}
