AddDataMember(struct __ecereNameSpace__ecere__com__Instance * parentRow, struct __ecereNameSpace__ecere__com__Instance * page, struct __ecereNameSpace__ecere__com__DataMember * member)
{
struct __ecereNameSpace__ecere__com__Instance * row;

if(member->type == 0)
{
row = __ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_AddRow(parentRow);
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_SetData(row, (((void *)0)), __extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_APIPage);

((struct APIPage *)(((char *)__ecereInstance1 + __ecereClass_APIPage->offset)))->name = member->name, ((struct APIPage *)(((char *)__ecereInstance1 + __ecereClass_APIPage->offset)))->page = page, __ecereInstance1;
}));
__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Set_icon(row, ((struct MainForm *)(((char *)mainForm + __ecereClass_MainForm->offset)))->icons[1]);
__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Set_tag(row, (long long)member);
}
else
{
struct __ecereNameSpace__ecere__com__DataMember * m;

row = __ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_AddRow(parentRow);
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_SetData(row, (((void *)0)), __extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_APIPage);

((struct APIPage *)(((char *)__ecereInstance1 + __ecereClass_APIPage->offset)))->name = (member->type == 1) ? "(union)" : "(struct)", ((struct APIPage *)(((char *)__ecereInstance1 + __ecereClass_APIPage->offset)))->page = page, __ecereInstance1;
}));
__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Set_icon(row, ((struct MainForm *)(((char *)mainForm + __ecereClass_MainForm->offset)))->icons[1]);
__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Set_tag(row, (long long)member);
for(m = member->members.first; m; m = m->next)
{
if(m->memberAccess == 1 || (m->memberAccess == 2 && ((struct APIPage *)(((char *)page + __ecereClass_APIPage->offset)))->showPrivate))
AddDataMember(row, page, m);
}
}
}
