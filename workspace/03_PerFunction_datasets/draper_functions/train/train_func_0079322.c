__ecereMethod___ecereNameSpace__eda__Row_Query(struct __ecereNameSpace__ecere__com__Instance * this, char * query)
{
struct __ecereNameSpace__eda__Row * __ecerePointer___ecereNameSpace__eda__Row = (struct __ecereNameSpace__eda__Row *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__Row->offset) : 0);

if(__ecerePointer___ecereNameSpace__eda__Row->row)
return ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char *  queryString))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__Row->row;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__eda__DriverRow->_vTbl;
})[__ecereVMethodID___ecereNameSpace__eda__DriverRow_Query])(__ecerePointer___ecereNameSpace__eda__Row->row, query);
return 0x0;
}
