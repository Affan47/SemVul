borg_think_home_buy_swap_armour(void)
{
    int hole;

    int n, b_n = -1;
    s32b p, b_p = 0L;
    bool fix = FALSE;
    int old_weapon_swap;
    s32b old_weapon_swap_value;
    int old_armour_swap;
    s32b old_armour_swap_value;


    old_weapon_swap = weapon_swap;
    old_weapon_swap_value =  weapon_swap_value;
    old_armour_swap = armour_swap;
    old_armour_swap_value =  armour_swap_value;

    if (armour_swap <= 1 || armour_swap_value <=0 )
    {
        hole = INVEN_MAX_PACK - 1;
        armour_swap_value = -1L;
    }
    else
    {
        hole = armour_swap;
    }


    b_p = armour_swap_value;


    for (n = 0; n < STORE_INVEN_MAX; n++)
    {
        borg_item *item = &borg_shops[7].ware[n];


        if (!item->iqty) continue;


        COPY(&safe_shops[7].ware[n], &borg_shops[7].ware[n], borg_item);


        COPY(&safe_items[hole], &borg_items[hole], borg_item);


        borg_shops[7].ware[n].iqty--;


        COPY(&borg_items[hole], &safe_shops[7].ware[n], borg_item);


        borg_items[hole].iqty = 1;


        fix = TRUE;


        borg_notice(TRUE);


        p = armour_swap_value;


        COPY(&borg_items[hole], &safe_items[hole], borg_item);


        COPY(&borg_shops[7].ware[n], &safe_shops[7].ware[n], borg_item);


        if (p <= b_p) continue;


        b_n = n; b_p = p;
    }


    if (fix) borg_notice(TRUE);


    if ((b_n >= 0) && (b_p > armour_swap_value))
    {

        goal_shop = 7;


        goal_ware = b_n;


        weapon_swap = old_weapon_swap;
        weapon_swap_value =  old_weapon_swap_value;
        armour_swap = old_armour_swap;
        armour_swap_value =  old_armour_swap_value;


        return (TRUE);
    }

    weapon_swap = old_weapon_swap;
    weapon_swap_value =  old_weapon_swap_value;
    armour_swap = old_armour_swap;
    armour_swap_value =  old_armour_swap_value;


    return (FALSE);
}
