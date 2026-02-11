ReformFuncList(void)
{
    FuncDict   func0_dict;
    SymbolDict sym_dict;

    (void)MakeDummyRfmFunc();
    (void)MakeDummyRfmFunc();

    func0_dict = commonp->func_managep->func[0];

    for (sym_dict = func0_dict->func_sym;
         sym_dict != NULL;
         sym_dict = sym_dict->next) {
        (void)MakeRfmFunc(sym_dict);
    }
}
