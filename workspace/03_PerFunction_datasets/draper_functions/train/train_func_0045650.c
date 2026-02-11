get_last_different_pair(List *list1, List *list2,
                        Block **block1, Block **block2)
{
    List *li1 = list_last(list1);
    List *li2 = list_last(list2);

    if (list_first_data(li1) != list_first_data(li2)) {
        *block1 = NULL;
        *block2 = NULL;

    } else {
        for (; li1 != NULL && li2 != NULL;
             li1 = li1->prev, li2 = li2->prev) {
            if (list_first_data(li1) != list_first_data(li2))
                break;
        }

        *block1 = list_first_data(li1);
        *block2 = list_first_data(li2);
    }

    return;
}
