dropWorkoutTable()
{
    QSqlQuery query("DROP TABLE workouts", dbconn);
    bool rc = query.exec();
    return rc;
}
