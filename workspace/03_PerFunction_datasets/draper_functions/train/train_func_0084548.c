__ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_OnPostCreate(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__dialogs__FileDialog * __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog = (struct __ecereNameSpace__ecere__gui__dialogs__FileDialog *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__dialogs__FileDialog->offset) : 0);

if(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->multiFilePaths)
{
int c;

for(c = 0; c < __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->numSelections; c++)
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->multiFilePaths[c]), __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->multiFilePaths[c] = 0);
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->multiFilePaths), __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->multiFilePaths = 0);
}
__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->numSelections = 0;
__ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_ListFiles(this);
{
char fileName[274];
char * dirOccur = strstr(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->filePath, __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->currentDirectory);

if(dirOccur)
{
dirOccur += strlen(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->currentDirectory);
for(; *dirOccur && (*dirOccur == '/' || *dirOccur == '\\'); dirOccur++)
;
strcpy(fileName, dirOccur);
}
else
strcpy(fileName, __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->filePath);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Clear(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_PutS(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName, fileName);
}
__ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_GetNameFromListBox(this, 0x0);
__ecereMethod___ecereNameSpace__ecere__gui__Window_MakeActive(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName);
return 0x1;
}
