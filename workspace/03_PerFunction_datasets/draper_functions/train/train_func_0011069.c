default_dict()
{
    static Cff *cff;
    static Cff::Font *cfffont;
    if (!cfffont) {
	cff = new Cff(String::make_stable((const char *) default_dict_cff_data, sizeof(default_dict_cff_data)), ErrorHandler::default_handler());
	cfffont = (Cff::Font *) cff->font();
    }
    return cfffont->top_dict();
}
