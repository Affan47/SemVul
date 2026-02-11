__ecereProp___ecereNameSpace__eda__DropDataBox_Set_filter(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int value)
{
struct __ecereNameSpace__eda__DropDataBox * __ecerePointer___ecereNameSpace__eda__DropDataBox = (struct __ecereNameSpace__eda__DropDataBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__DropDataBox->offset) : 0);

__ecerePointer___ecereNameSpace__eda__DropDataBox->filtered = 0x1;
__ecerePointer___ecereNameSpace__eda__DropDataBox->filter = value;
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__eda__DropDataBox_filter), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__eda__DropDataBox_filter);
}
