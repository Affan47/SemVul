v5dWrite(int time, int var, const float data[])
{
    if (Simple) {
	if (time < 1 || time > Simple->NumTimes) {
	    printf("Error in v5dWrite: bad timestep number: %d\n", time);
	    return 0;
	}
	if (var < 1 || var > Simple->NumVars) {
	    printf("Error in v5dWrite: bad variable number: %d\n", var);
	}
	return v5dWriteGrid(Simple, time - 1, var - 1, data);
    }
    else {
	printf("Error: must call v5dCreate before v5dWrite\n");
	return 0;
    }
}
