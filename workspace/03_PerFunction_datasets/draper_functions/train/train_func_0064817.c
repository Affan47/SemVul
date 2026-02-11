FoPop( int k )
#else
FoPop( k )
int k;
#endif
{
	require(k<=CLL_k, "FoPop: tried to access non-existent stack");

	require(FoTOS[k]>=FoStack[k]&&FoTOS[k]<=&(FoStack[k][FoStackSize-1]),
			"FoPop: FoStack stack-ptr is playing out of its sandbox");
	if ( FoTOS[k] == FoStack[k] ) FoTOS[k] = NULL;
	else (FoTOS[k])--;
}
