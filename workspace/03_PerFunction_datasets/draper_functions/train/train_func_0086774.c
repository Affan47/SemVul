__ecereProp___ecereNameSpace__ecere__PaneSplitter_Set_scaleSplit(struct __ecereNameSpace__ecere__com__Instance * this, double value)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
struct __ecereNameSpace__ecere__PaneSplitter * __ecerePointer___ecereNameSpace__ecere__PaneSplitter = (struct __ecereNameSpace__ecere__PaneSplitter *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__PaneSplitter->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__PaneSplitter->scaleSplit = value;
__ecereProp___ecereNameSpace__ecere__PaneSplitter_Set_split(this, ((int)(((__ecerePointer___ecereNameSpace__ecere__PaneSplitter->orientation == 1) ? (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), &__simpleStruct0), __simpleStruct0).w : (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), &__simpleStruct1), __simpleStruct1).h) * (value) + 0.5)));
__ecerePointer___ecereNameSpace__ecere__PaneSplitter->scale = 0x1;
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__ecere__PaneSplitter_scaleSplit), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__ecere__PaneSplitter_scaleSplit);
}
