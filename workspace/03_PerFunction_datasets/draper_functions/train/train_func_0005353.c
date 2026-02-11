output_number(double coord, int axis, char *buffer) {


    if (axis_array[axis].datatype == DT_TIMEDATE &&
	strcmp(axis_array[axis].formatstring, "%s") == 0) {
	gprintf(buffer, BUFFERSIZE, "%.0f", 1.0, coord);
    } else
    if (axis_array[axis].datatype == DT_TIMEDATE) {
	buffer[0] = '"';
	gstrftime(buffer+1, BUFFERSIZE-1, axis_array[axis].formatstring, coord);
	while (strchr(buffer,'\n')) {*(strchr(buffer,'\n')) = ' ';}
	strcat(buffer,"\"");
    } else if (axis_array[axis].log) {
	double x = pow(axis_array[axis].base, coord);
	gprintf(buffer, BUFFERSIZE, axis_array[axis].formatstring, 1.0, x);
    } else
	gprintf(buffer, BUFFERSIZE, axis_array[axis].formatstring, 1.0, coord);
    fputs(buffer, outfile);
    fputc(' ', outfile);
}
