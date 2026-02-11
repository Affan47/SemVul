gga_second(FunSecondFuncDrv *ds, real factor, const FunDensProp* dp)
{
    FuncList* lst;
    for(lst=gga_fun_list; lst; lst=lst->next)
        lst->func->second(ds, factor*lst->weight, dp);
}
