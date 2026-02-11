__ecereMethod___ecereNameSpace__ecere__gui__controls__UndoBuffer_Redo(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__UndoBuffer * __ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer = (struct __ecereNameSpace__ecere__gui__controls__UndoBuffer *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__UndoBuffer->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->dontRecord++;
__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->insideRedo = 0x1;
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->curAction < __ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->count)
{
struct __ecereNameSpace__ecere__gui__controls__UndoAction * action = ((struct __ecereNameSpace__ecere__gui__controls__UndoAction **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->actions + 24)))->array)[__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->curAction];

__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->curAction++;
((void (*)(struct __ecereNameSpace__ecere__gui__controls__UndoAction *, void *  data))__ecereClass___ecereNameSpace__ecere__gui__controls__UndoAction->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__controls__UndoAction_Redo])(action, __ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->data);
}
__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->insideRedo = 0x0;
__ecerePointer___ecereNameSpace__ecere__gui__controls__UndoBuffer->dontRecord--;
}
