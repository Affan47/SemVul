jpeg_put_params(gx_device * dev, gs_param_list * plist)
{
    gx_device_jpeg *jdev = (gx_device_jpeg *) dev;
    int ecode = 0;
    int code;
    gs_param_name param_name;
    int jq = jdev->JPEGQ;
    float qf = jdev->QFactor;
    float fparam;

    switch (code = param_read_int(plist, (param_name = "JPEGQ"), &jq)) {
        case 0:
            if (jq < 0 || jq > 100)
                ecode = gs_error_limitcheck;
            else
                break;
            goto jqe;
        default:
            ecode = code;
          jqe:param_signal_error(plist, param_name, ecode);
        case 1:
            break;
    }

    switch (code = param_read_float(plist, (param_name = "QFactor"), &qf)) {
        case 0:
            if (qf < 0.0 || qf > 1.0e6)
                ecode = gs_error_limitcheck;
            else
                break;
            goto qfe;
        default:
            ecode = code;
          qfe:param_signal_error(plist, param_name, ecode);
        case 1:
            break;
    }

    code = param_read_float(plist, (param_name = "ViewScaleX"), &fparam);
    if ( code == 0 ) {
        if (fparam < 1.0)
            param_signal_error(plist, param_name, gs_error_limitcheck);
        else
            jdev->ViewScale.x = fparam;
    }
    else if ( code < 1 ) {
        ecode = code;
        param_signal_error(plist, param_name, code);
    }

    code = param_read_float(plist, (param_name = "ViewScaleY"), &fparam);
    if ( code == 0 ) {
        if (fparam < 1.0)
            param_signal_error(plist, param_name, gs_error_limitcheck);
        else
            jdev->ViewScale.y = fparam;
    }
    else if ( code < 1 ) {
        ecode = code;
        param_signal_error(plist, param_name, code);
    }


    code = param_read_float(plist, (param_name = "ViewTransX"), &fparam);
    if ( code == 0 ) {
        jdev->ViewTrans.x = fparam;
    }
    else if ( code < 1 ) {
        ecode = code;
        param_signal_error(plist, param_name, code);
    }

    code = param_read_float(plist, (param_name = "ViewTransY"), &fparam);
    if ( code == 0 ) {
        jdev->ViewTrans.y = fparam;
    }
    else if ( code < 1 ) {
        ecode = code;
        param_signal_error(plist, param_name, code);
    }
    code = gdev_prn_put_params(dev, plist);
    if (code < 0)
        return code;

    if (ecode < 0)
        return ecode;

    jdev->JPEGQ = jq;
    jdev->QFactor = qf;
    return 0;
}
