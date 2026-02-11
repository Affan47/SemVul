Pk11Install_PlatformName_lteq(Pk11Install_PlatformName* _this,
                              Pk11Install_PlatformName* cmp)
{
	return (Pk11Install_PlatformName_equal(_this,cmp) ||
          Pk11Install_PlatformName_lt(_this,cmp)) ? PR_TRUE : PR_FALSE;
}
