initCliArgs()
{

    KCmdLineOptions options;

    options.add("+[URL(s)]", ki18n( "Files/URLs to open" ));
    options.add("cdplay", ki18n("Immediately start playing an audio cd"));
    options.add("r");
    options.add("previous", ki18n( "Skip backwards in playlist" ));
    options.add("p");
    options.add("play", ki18n( "Start playing current playlist" ));
    options.add("t");
    options.add("play-pause", ki18n( "Play if stopped, pause if playing" ));
    options.add("pause", ki18n( "Pause playback" ));
    options.add("s");
    options.add("stop", ki18n( "Stop playback" ));
    options.add("f");
    options.add("next", ki18n( "Skip forwards in playlist" ));
    options.add(":", ki18n("Additional options:"));
    options.add("a");
    options.add("append", ki18n( "Append files/URLs to playlist" ));
    options.add("queue", ki18n("Queue URLs after the currently playing track"));
    options.add("l");
    options.add("load", ki18n("Load URLs, replacing current playlist"));
    options.add("d");
    options.add("debug", ki18n("Print verbose debugging information"));
    options.add("debug-audio", ki18n("Print verbose debugging information from the audio system"));
    options.add("c");
    options.add("coloroff", ki18n("Disable colorization for debug output."));
    options.add("m");
    options.add("multipleinstances", ki18n("Allow running multiple Amarok instances"));
    options.add("cwd <directory>", ki18n( "Base for relative filenames/URLs" ));

    KCmdLineArgs::addCmdLineOptions( options );
}
