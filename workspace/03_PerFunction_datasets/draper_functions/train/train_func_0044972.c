term_list_get_common_term(List *term_list1, List *term_list2)
{
    List *li1, *li2;
    List *common_list = NULL;

    for (li1 = term_list1; li1 != NULL; li1 = li1->next) {
        Term *p1 = list_first_data(li1);

        for (li2 = term_list2; li2 != NULL; li2 = li2->next) {
            Term *p2 = list_first_data(li2);

            if (term_is_equal(p1, p2))
                break;
        }

        if (li2 != NULL) {
            common_list = list_append(common_list, p1);
        }
    }

    return common_list;
}
