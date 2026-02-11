from_tk_ReadModelPropertyData(ClientData clientData, Tcl_Interp *interp,
          int argc, char* argv[])
{
  Model* model = theControlCenter->getModel();

  if (model == NULL) {
    TheUI->errMsg(0, "ReadModelPropertyData: Command not legal. No model exists!");
    return TCL_OK;
  }


  char* name1 = NULL;
  char* name2 = NULL;

  char* desc1 = NULL;
  char* desc2 = NULL;

  char* dir1 = NULL;
  char* dir2 = NULL;
  char* dir3 = NULL;
  char* dir4 = NULL;

  char* dir1_abs = NULL;
  char* dir2_abs = NULL;
  char* dir3_abs = NULL;
  char* dir4_abs = NULL;

  int dir2_save = 0;
  int dir3_save = 0;
  int dir4_save = 0;


  readVariable(interp, "ModelProperty", "MODEL_NAME", name1);
  readVariable(interp, "ModelProperty", "PROBLEM_NAME", name2);
  model->setModelNames(name1, name2);


  readVariable(interp, "ModelProperty", "MODEL_DESCRIPTION", desc1);
  readVariable(interp, "ModelProperty", "PROBLEM_DESCRIPTION", desc2);
  model->setModelDescriptions(desc1, desc2);


  readVariable(interp, "ModelProperty", "MODEL_DIRECTORY", dir1);
  readVariable(interp, "ModelProperty", "MODEL_DIRECTORY,absolute", dir1_abs);

  readVariable(interp, "ModelProperty", "INCLUDE_PATH", dir2);
  readVariable(interp, "ModelProperty", "INCLUDE_PATH,absolute", dir2_abs);
  readVariable(interp, "ModelProperty", "INCLUDE_PATH,model,save", dir2_save);

  readVariable(interp, "ModelProperty", "RESULTS_DIRECTORY", dir3);
  readVariable(interp, "ModelProperty", "RESULTS_DIRECTORY,absolute", dir3_abs);
  readVariable(interp, "ModelProperty", "RESULTS_DIRECTORY,model,save", dir3_save);

  readVariable(interp, "ModelProperty", "LOG_DIRECTORY", dir4);
  readVariable(interp, "ModelProperty", "LOG_DIRECTORY,absolute", dir4_abs);
  readVariable(interp, "ModelProperty", "LOG_DIRECTORY,model,save", dir4_save);

  model->setModelFileDirectories(dir1, dir2, dir3, dir4);
  model->setModelFileDirectoriesAbs(dir1_abs, dir2_abs, dir3_abs, dir4_abs);
  model->setModelFileDirectoriesSave(dir2_save, dir3_save, dir4_save);


  delete[] name1; delete[] name2;
  delete[] desc1; delete[] desc2;
  delete[] dir1; delete[] dir2; delete[] dir3; delete[] dir4;
  delete[] dir1_abs; delete[] dir2_abs; delete[] dir3_abs; delete[] dir4_abs;

  return TCL_OK;
}
