__ecereProp___ecereNameSpace__eda__EDBRow_Set_num(struct __ecereNameSpace__ecere__com__Instance * this, int value)
{
struct __ecereNameSpace__eda__EDBRow * __ecerePointer___ecereNameSpace__eda__EDBRow = (struct __ecereNameSpace__eda__EDBRow *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__EDBRow->offset) : 0);

__ecerePointer___ecereNameSpace__eda__EDBRow->_num = value;
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__eda__EDBRow->aname), __ecerePointer___ecereNameSpace__eda__EDBRow->aname = 0);
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__eda__EDBRow_num), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__eda__EDBRow_num);
}
