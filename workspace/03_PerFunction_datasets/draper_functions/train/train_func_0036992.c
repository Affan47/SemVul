writeStaticMFile(const string &func_name) const
{

  string filename = func_name + "_static.m";

  ofstream output;
  output.open(filename.c_str(), ios::out | ios::binary);
  if (!output.is_open())
    {
      cerr << "ERROR: Can't open file " << filename << " for writing" << endl;
      exit(EXIT_FAILURE);
    }

  output << "function [residual, g1, g2] = " << func_name + "_static(y, x, params)" << endl
         << "%" << endl
         << "% Status : Computes static model for Dynare" << endl
         << "%" << endl
         << "% Inputs : " << endl
         << "%   y         [M_.endo_nbr by 1] double    vector of endogenous variables in declaration order" << endl
         << "%   x         [M_.exo_nbr by 1] double     vector of exogenous variables in declaration order" << endl
         << "%   params    [M_.param_nbr by 1] double   vector of parameter values in declaration order" << endl
         << "%" << endl
         << "% Outputs:" << endl
         << "%   residual  [M_.endo_nbr by 1] double    vector of residuals of the static model equations " << endl
         << "%                                          in order of declaration of the equations" << endl
         << "%   g1        [M_.endo_nbr by M_.endo_nbr] double    Jacobian matrix of the static model equations;" << endl
         << "%                                                    columns: equations in order of declaration" << endl
         << "%                                                    rows: variables in declaration order" << endl
         << "%   g2        [M_.endo_nbr by (M_.endo_nbr)^2] double   Hessian matrix of the static model equations;" << endl
         << "%                                                       columns: equations in order of declaration" << endl
         << "%                                                       rows: variables in declaration order" << endl
         << "%" << endl
         << "%" << endl
         << "% Warning : this file is generated automatically by Dynare" << endl
         << "%           from model file (.mod)" << endl << endl;

  writeStaticModel(output, false);
  output << "end" << endl;
  output.close();
}
