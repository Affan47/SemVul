Check_Callback_List (Object x) {
    Object tail;

    Check_List (x);
    for (tail = x; !Nullp (tail); tail = Cdr (tail))
        Check_Procedure (Car (tail));
}
