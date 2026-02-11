ThinkSurvive(  ThinkData & data )
{
    if (!character)
    {
        st_Breakpoint();
        return;
    }

    REAL random = 0;


    if (data.left.front.wallType == gSENSOR_RIM)
        EmergencySurvive( data, 1);
    else if (data.right.front.wallType == gSENSOR_RIM)
        EmergencySurvive( data, -1);
    else
        EmergencySurvive( data );


    if (nextStateChange > se_GameTime())
    {
        data.thinkAgain = .5f;
        return;
    }


    random=10*Random();
    if (random < 5)
    {

        eCoord enemypos=eCoord(1000,100);

        const tList<eGameObject>& gameObjects = Object()->Grid()->GameObjects();
        gCycle *secondbest = NULL;


        for (int i=gameObjects.Len()-1;i>=0;i--){
            gCycle *other=dynamic_cast<gCycle *>(gameObjects(i));

            if (other && other->Team()!=Object()->Team() &&
                    !IsTrapped(other, Object())){

                eCoord otherpos=other->Position()-Object()->Position();
                if (otherpos.NormSquared()<enemypos.NormSquared()){

                    gSensor p(Object(),Object()->Position(),otherpos);
                    p.detect(REAL(.98));
                    secondbest = dynamic_cast<gCycle *>(other);
                    if (p.hit>=.98){
                        enemypos = otherpos;
                        target = secondbest;
                    }
                }
            }
        }

        if (!target)
            target = secondbest;

        if (target)
            SwitchToState(AI_CLOSECOMBAT, 1);
    }

    data.thinkAgain = 1;
}
