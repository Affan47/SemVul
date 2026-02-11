P_Atan (int argc, Object *argv) {
    register int a2 = argc == 2;
    return General_Function (argv[0], a2 ? argv[1] : Null, a2 ?
        (double(*)())atan2 : (double(*)())atan);
}
