HDGLremove_from_beginning(Generic_list list)
{
    Generic_list_element *element;
    VOIDP pointer;
    VOIDP ret_value = NULL;


    if(list.info->num_of_elements == 0)
      {
        ret_value = NULL;
        goto done;
      }


    element = list.info->pre_element.next;
    if (element == list.info->current)
        list.info->current = &list.info->pre_element;

    pointer = element->pointer;
    list.info->pre_element.next = element->next;
    element->next->previous = &list.info->pre_element;

    HDfree(element);
    list.info->num_of_elements--;

    ret_value = pointer;

done:
    if (ret_value == NULL)
      {
      }

return ret_value;
}
