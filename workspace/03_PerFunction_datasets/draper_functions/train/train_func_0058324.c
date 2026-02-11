pay_for_amount(uint64 to_pay, object *pl) {
    if (to_pay == 0)
        return 1;
    if (to_pay > query_money(pl))
        return 0;

    to_pay = pay_from_container(pl, pl, to_pay);

    FOR_INV_PREPARE(pl, pouch) {
        if (to_pay <= 0)
            break;
        if (pouch->type == CONTAINER
        && QUERY_FLAG(pouch, FLAG_APPLIED)
        && (pouch->race == NULL || strstr(pouch->race, "gold"))) {
            to_pay = pay_from_container(pl, pouch, to_pay);
        }
    } FOR_INV_FINISH();
    if (to_pay > 0) {
        LOG(llevError, "pay_for_amount: Cannot remove enough money -- %"FMT64U" remains\n", to_pay);
    }

    fix_object(pl);
    return 1;
}
