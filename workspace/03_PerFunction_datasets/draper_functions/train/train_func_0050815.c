borg_send_inscribe(int i, char *str)
{
    char *s;


    borg_keypress(c1);


    if (i < INVEN_WIELD)
    {

        borg_keypress(I2A(i));
    }


    else
    {

        if (borg_items[0].iqty) borg_keypress('/');


        borg_keypress(I2A(i - INVEN_WIELD));
    }


    for (s = str; *s; s++) borg_keypress(*s);


    borg_keypress('\n');

}
