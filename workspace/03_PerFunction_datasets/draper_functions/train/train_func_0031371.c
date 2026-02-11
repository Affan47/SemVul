operator=(Real f)
{ REPORT int i=storage; Real* s=store; while (i--) { *s++ = f; } }
