_cx_deque_shift_left(cx_deque *deque, cxsize n, cxsize position, cxsize size)
{

#if 0

    cxsize i = 0;


    for (i = 0; i < size; ++i) {

        register cxsize current = deque->front + position + i;

        deque->members[current - n] = deque->members[current];

    }

    return;

#else

    if (n > 0) {

        register cxsize start = deque->front + position;

        memmove(&deque->members[start - n],
                &deque->members[start], size * sizeof(cxptr));

    }

    return;

#endif

}
