recoverSuspendedTask (Capability *cap, Task *task)
{
    InCall *incall;

    incall = task->incall;
    if (incall->prev) {
	incall->prev->next = incall->next;
    } else {
	ASSERT(cap->suspended_ccalls == incall);
	cap->suspended_ccalls = incall->next;
    }
    if (incall->next) {
	incall->next->prev = incall->prev;
    }
    incall->next = incall->prev = NULL;
}
