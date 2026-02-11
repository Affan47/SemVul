__ecereProp___ecereNameSpace__eda__ListSection_Set_editor(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * value)
{
struct __ecereNameSpace__eda__ListSection * __ecerePointer___ecereNameSpace__eda__ListSection = (struct __ecereNameSpace__eda__ListSection *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__ListSection->offset) : 0);

__ecerePointer___ecereNameSpace__eda__ListSection->editor = value;
((struct __ecereNameSpace__eda__EditSection *)(((char *)value + __ecereClass___ecereNameSpace__eda__EditSection->offset)))->list = this;
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__eda__ListSection_editor), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__eda__ListSection_editor);
}
