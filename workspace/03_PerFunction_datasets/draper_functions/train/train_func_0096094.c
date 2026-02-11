Execute () {
    static char* default_rotatestr = strdup("45.0");
    char* rotatestr =
      StrEditDialog::post(GetEditor()->GetWindow(),
			  "Enter rotation in degrees:",
			  default_rotatestr, "Precise Rotate");
    if (rotatestr) {
      std::istrstream in(rotatestr);
      float angle = 0.0;
      in >> angle;
      if (angle!=0.0) {
	RotateCmd* rotateCmd = new RotateCmd(GetEditor(), angle);
	rotateCmd->Execute();
	rotateCmd->Log();
      }
      delete default_rotatestr;
      default_rotatestr = rotatestr;
    }
}
