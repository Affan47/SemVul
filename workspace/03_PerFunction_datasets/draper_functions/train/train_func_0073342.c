writeCast(int e1, int e2) {

  if((e1 != TIPO_REAL) && (e2 == TIPO_REAL)) {

    writeTEXT("mov dword [aux], eax");
    writeTEXT("fild dword [aux]");
    writeTEXT("fstp dword [aux]");
    writeTEXT("mov eax, dword [aux]");
  } else if((e1 == TIPO_REAL) && (e2 != TIPO_REAL)) {


    writeTEXT("fnstcw word [aux2]");
    writeTEXT("mov dx, word [aux2]");
    writeTEXT("mov dh, 0xc");
    writeTEXT("mov word [aux], dx");
    writeTEXT("fldcw word [aux]");

    writeTEXT("mov dword [aux], eax");
    writeTEXT("fld dword [aux]");
    writeTEXT("fistp dword [aux]");
    writeTEXT("mov eax, dword [aux]");


    writeTEXT("fldcw word [aux2]");
  }
}
