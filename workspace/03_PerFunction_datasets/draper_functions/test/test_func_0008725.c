newRenderCompleted(const WallpaperRenderRequest &request, const QImage &image)
{
    kDebug() << request.token << renderToken;
    if (request.token != renderToken) {

        return;
    }

    if (cacheRendering) {
        q->insertIntoCache(cacheKey(request.file, request.size, request.resizeMethod, request.color), image);
    }


    emit q->renderCompleted(image);
}
