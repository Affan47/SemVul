mp3tunes_locker_upload_track(mp3tunes_locker_object_t *obj, const char *path) {
    request_t *request;
    FILE * hd_src ;
    int hd ;
    struct stat file_info;
    char* file_key = mp3tunes_locker_generate_filekey(path);

    if (file_key == NULL)
        return -1;


    hd = open(path, O_RDONLY);
    if (hd == -1) {
        free(file_key);
        return -1;
    }

    fstat(hd, &file_info);
    close(hd);

    hd_src = fopen(path, "rb");


    char *url = malloc(256*sizeof(char));
    snprintf(url, 256, "storage/lockerput/%s", file_key);
    free(file_key);
    request = mp3tunes_locker_api_generate_request(obj, MP3TUNES_SERVER_CONTENT, url, NULL);
    if (request == NULL) {
        fclose(hd_src);
        return -1;
    }


    curl_easy_setopt( request->curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt( request->curl, CURLOPT_PUT, 1L);
    curl_easy_setopt( request->curl, CURLOPT_URL, request->url);
    curl_easy_setopt( request->curl, CURLOPT_READDATA, hd_src);
    curl_easy_setopt( request->curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
    curl_easy_setopt( request->curl, CURLOPT_USERAGENT, "liboboe/1.0" );


    curl_easy_perform(request->curl);

    mp3tunes_request_deinit(&request);
    free(url);

    fclose(hd_src);
    return 0;
}
