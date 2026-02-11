getXferSyntax(DCM_OBJECT** iod, char* fileXferSyntax)
{
  CONDITION cond;
  DCM_ELEMENT elements[] = {
	{DCM_METATRANSFERSYNTAX, DCM_UI, "", 1, 65, 0}
    };

  elements[0].d.string = fileXferSyntax;
  cond = DCM_ParseObject(iod, elements, DIM_OF(elements), NULL, 0, NULL);
  if (cond != DCM_NORMAL) {
    printf("Unable to get Transfer Syntax from Part 10 file\n");
    exit(1);
  }
}
