mini_gc_free(void *ptr)
{
    Header *target, *hit;

    target = (Header *)ptr - 1;


    for (hit = free_list; !(target > hit && target < hit->next_free); hit = hit->next_free)

        if (hit >= hit->next_free &&
            (target > hit || target < hit->next_free))
            break;

    if (NEXT_HEADER(target) == hit->next_free) {

        target->size += (hit->next_free->size + HEADER_SIZE);
        target->next_free = hit->next_free->next_free;
    }
    else {

        target->next_free = hit->next_free;
    }
    if (NEXT_HEADER(hit) == target) {

        hit->size += (target->size + HEADER_SIZE);
        hit->next_free = target->next_free;
    }
    else {

        hit->next_free = target;
    }
    free_list = hit;
    target->flags = 0;
}
