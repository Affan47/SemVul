refresh_city_names(struct city *pCity)
{
  if (pCityDlg->pCity_Name_Edit) {
    char name[MAX_LEN_NAME];

    convertcopy_to_chars(name, MAX_LEN_NAME,
			    pCityDlg->pCity_Name_Edit->string16->text);
    if ((strcmp(city_name(pCity), name) != 0)
      || (SDL_Client_Flags & CF_CHANGED_CITY_NAME)) {
      copy_chars_to_string16(pCityDlg->pCity_Name_Edit->string16, city_name(pCity));
      rebuild_citydlg_title_str(pCityDlg->pEndCityWidgetList, pCity);
      SDL_Client_Flags &= ~CF_CHANGED_CITY_NAME;
    }
  }
}
