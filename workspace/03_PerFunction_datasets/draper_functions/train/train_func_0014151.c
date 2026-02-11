__ecereMethod_Debugger_GetMarginIconsLineNumbers(struct __ecereNameSpace__ecere__com__Instance * this, char * fileName, int lines[], unsigned int enabled[], int max, unsigned int * error, int * lineCursor, int * lineTopFrame)
{
struct Debugger * __ecerePointer_Debugger = (struct Debugger *)(this ? (((char *)this) + __ecereClass_Debugger->offset) : 0);
char winFilePath[797];
char * absoluteFilePath = __ecereFunction___ecereNameSpace__ecere__sys__GetSlashPathBuffer(winFilePath, fileName);
int count = 0;
struct __ecereNameSpace__ecere__com__Iterator it =
{
__extension__ ({
char * __ecTemp1 = (__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace));

((struct Workspace *)(__ecTemp1 + __ecereClass_Workspace->offset));
})->breakpoints, 0
};

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&it) && count < max)
{
struct Breakpoint * bp = ((struct Breakpoint *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&it));

if(bp->type == 4)
{
if(bp->absoluteFilePath && bp->absoluteFilePath[0] && !((__ecereFunction___ecereNameSpace__ecere__com__GetRuntimePlatform() == 1) ? (strcasecmp) : strcmp)(bp->absoluteFilePath, absoluteFilePath))
{
lines[count] = bp->line;
enabled[count] = bp->enabled;
count++;
}
}
}
if(__ecerePointer_Debugger->activeFrameLevel == -1)
{
*error = 0x0;
*lineCursor = 0;
*lineTopFrame = 0;
}
else
{
*error = __ecerePointer_Debugger->signalOn && __ecerePointer_Debugger->activeThread == __ecerePointer_Debugger->signalThread;
if(__ecerePointer_Debugger->activeFrame && __ecerePointer_Debugger->activeFrame->absoluteFile && !((__ecereFunction___ecereNameSpace__ecere__com__GetRuntimePlatform() == 1) ? (strcasecmp) : strcmp)(absoluteFilePath, __ecerePointer_Debugger->activeFrame->absoluteFile))
*lineCursor = __ecerePointer_Debugger->activeFrame->line;
else
*lineCursor = 0;
if(__ecerePointer_Debugger->activeFrame && __ecerePointer_Debugger->stopItem && __ecerePointer_Debugger->stopItem->frame && __ecerePointer_Debugger->activeFrame->level == __ecerePointer_Debugger->stopItem->frame->level)
*lineTopFrame = 0;
else if(__ecerePointer_Debugger->stopItem && __ecerePointer_Debugger->stopItem->frame && __ecerePointer_Debugger->stopItem->frame->absoluteFile && !((__ecereFunction___ecereNameSpace__ecere__com__GetRuntimePlatform() == 1) ? (strcasecmp) : strcmp)(absoluteFilePath, __ecerePointer_Debugger->stopItem->frame->absoluteFile))
*lineTopFrame = __ecerePointer_Debugger->stopItem->frame->line;
else
*lineTopFrame = 0;
if(*lineTopFrame == *lineCursor && *lineTopFrame)
*lineTopFrame = 0;
}
return count;
}
