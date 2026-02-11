locker (aso, exp)
     Af_key *aso;
     Expr exp;
{
  Af_user cmpUser, *asoUser;

  atScanUser ((char *)exp->left, &cmpUser);
  asoUser = af_retuserattr (aso, AF_ATTLOCKER);

  return (!strcmp (cmpUser.af_username, asoUser->af_username)
	  && !strcmp (cmpUser.af_userdomain, asoUser->af_userdomain));
}
