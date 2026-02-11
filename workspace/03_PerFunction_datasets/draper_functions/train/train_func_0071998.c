attach(Microtek2_Device *md)
{


    SANE_String model_string;
    SANE_Status status;
    SANE_Byte source_info;


    DBG(30, "attach: device='%s'\n", md->name);

    status = scsi_inquiry( &md->info[MD_SOURCE_FLATBED], md->name );
    if ( status != SANE_STATUS_GOOD )
      {
	DBG(1, "attach: '%s'\n", sane_strstatus(status));
        return status;
      }


    for ( source_info = 1; source_info < 5; ++source_info )
        memcpy( &md->info[source_info],
                &md->info[MD_SOURCE_FLATBED],
                sizeof( Microtek2_Info ) );


    status = check_inquiry(md, &model_string);
    if ( status != SANE_STATUS_GOOD )
        return status;

    md->sane.name = md->name;
    md->sane.vendor = "Microtek";
    md->sane.model = strdup(model_string);
    if ( md->sane.model == NULL )
        DBG(1, "attach: strdup for model string failed\n");
    md->sane.type = "flatbed scanner";
    md->revision = strtod(md->info[MD_SOURCE_FLATBED].revision, NULL);

    status = scsi_read_attributes(&md->info[0],
                                  md->name, MD_SOURCE_FLATBED);
    if ( status != SANE_STATUS_GOOD )
      {
	DBG(1, "attach: '%s'\n", sane_strstatus(status));
        return status;
      }

    if ( MI_LUTCAP_NONE( md->info[MD_SOURCE_FLATBED].lut_cap) )

        md->model_flags |= MD_NO_GAMMA;


    if ( md->info[MD_SOURCE_FLATBED].option_device & MI_OPTDEV_TMA )
      {
        status = scsi_read_attributes(&md->info[0],
                                      md->name, MD_SOURCE_TMA);
        if ( status != SANE_STATUS_GOOD )
            return status;
      }


    if ( md->info[MD_SOURCE_FLATBED].option_device & MI_OPTDEV_ADF )
      {
        status = scsi_read_attributes(&md->info[0],
                                      md->name, MD_SOURCE_ADF);
        if ( status != SANE_STATUS_GOOD )
            return status;
      }


    if ( md->info[MD_SOURCE_FLATBED].option_device & MI_OPTDEV_STRIPE )
      {
        status = scsi_read_attributes(&md->info[0],
                                      md->name, MD_SOURCE_STRIPE);
        if ( status != SANE_STATUS_GOOD )
            return status;
      }


    if ( md->info[MD_SOURCE_FLATBED].option_device & MI_OPTDEV_SLIDE )
      {


        if ( ! (md->model_flags & MD_NO_SLIDE_MODE) )
          {
            status = scsi_read_attributes(&md->info[0],
                                          md->name, MD_SOURCE_SLIDE);
            if ( status != SANE_STATUS_GOOD )
                return status;
          }
      }

    status = scsi_read_system_status(md, -1);
    if ( status != SANE_STATUS_GOOD )
        return status;

    return SANE_STATUS_GOOD;
}
