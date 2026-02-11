borg_keypress(char k)
{

    if (!k) return (-1);


   	borg_note(format("& Key <%c>", k));


    borg_key_queue[borg_key_head++] = k;


    if (borg_key_head == KEY_SIZE) borg_key_head = 0;


    if (borg_key_head == borg_key_tail) borg_oops("overflow");


    if (borg_key_tail == KEY_SIZE) borg_key_tail = 0;


    return (0);
}
