Parse(MIOFILE& in) {
    char buf[256];
    std::string strBuffer;

    while (in.fgets(buf, 256)) {
        if (match_tag(buf, "</simple>")) break;
        else if (match_tag(buf, "<background_image>")) {
            m_BackgroundImage.Parse(in);
            continue;
        } else if (match_tag(buf, "<dialog_background_image>")) {
            m_DialogBackgroundImage.Parse(in);
            continue;
        } else if (match_tag(buf, "<project_image>")) {
            m_ProjectImage.Parse(in);
            continue;
        } else if (parse_str(buf, "<static_line_color>", strBuffer)) {
            m_StaticLineColor = ParseColor(wxString(strBuffer.c_str(), wxConvUTF8));
            continue;
        } else if (parse_str(buf, "<notice_alert_color>", strBuffer)) {
            m_NoticeAlertColor = ParseColor(wxString(strBuffer.c_str(), wxConvUTF8));
            continue;
        } else if (match_tag(buf, "<workunit_animation_image>")) {
            m_WorkunitAnimationImage.Parse(in);
            continue;
        } else if (match_tag(buf, "<workunit_running_image>")) {
            m_WorkunitRunningImage.Parse(in);
            continue;
        } else if (match_tag(buf, "<workunit_suspended_image>")) {
            m_WorkunitSuspendedImage.Parse(in);
            continue;
        } else if (match_tag(buf, "<workunit_waiting_image>")) {
            m_WorkunitWaitingImage.Parse(in);
            continue;
        } else if (parse_int(buf, "<panel_opacity>", m_iPanelOpacity)) {
            continue;
        }
    }

    InitializeDelayedValidation();

    return 0;
}
