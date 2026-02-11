write_team(TEAM& team, FILE* f, bool detail) {
    DB_USER user;
    char buf[256];
    char name[2048];
    char url[2048], name_html[2048];
    int retval;
    char description[BLOB_SIZE];

    xml_escape(team.name, name, sizeof(name));

    fprintf(f,
        "<team>\n"
        " <id>%d</id>\n"
        " <type>%d</type>\n"
        " <name>%s</name>\n"
        " <userid>%d</userid>\n"
        " <total_credit>%f</total_credit>\n"
        " <expavg_credit>%f</expavg_credit>\n"
        " <expavg_time>%f</expavg_time>\n",
        team.id,
        team.type,
        name,
        team.userid,
        team.total_credit,
        team.expavg_credit,
        team.expavg_time
    );


    retval = user.lookup_id(team.userid);
    if (!retval) {
        char fname[2048];
        xml_escape(user.name, fname, sizeof(fname));
        fprintf(f,
            "  <founder_name>%s</founder_name>\n",
            fname
        );
    }

    fprintf(f,
        " <create_time>%d</create_time>\n",
        team.create_time
    );
    if (strlen(team.url)) {
        xml_escape(team.url, url, sizeof(url));
        fprintf(f,
            " <url>%s</url>\n",
            url
        );
    }
    if (strlen(team.name_html)) {
        xml_escape(team.name_html, name_html, sizeof(name_html));
        fprintf(f,
            "<name_html>%s</name_html>\n",
            name_html
        );
    }

    if (strlen(team.description)) {
        xml_escape(team.description, description, sizeof(description));
        fprintf(f,
            "<description>%s</description>\n",
            description
        );
    }

    fprintf(f,
        " <country>%s</country>\n",
        team.country
    );
    if (detail) {
        sprintf(buf, "where teamid=%d", team.id);
        while (1) {
            retval = user.enumerate(buf);
            if (retval) break;
            write_user(user, f, false);
        }
        if (retval != ERR_DB_NOT_FOUND) {
            log_messages.printf(MSG_CRITICAL,
                "user enum: %s", boincerror(retval)
            );
            exit(retval);
        }
    }
    fprintf(f,
        "</team>\n"
    );
}
